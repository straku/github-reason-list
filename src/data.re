type repo = {
  cursor: string,
  name: string,
  url: string,
  description: option(string),
  ownerLogin: string,
  ownerAvatarUrl: string,
  stars: int,
  language: option(string),
};

let url = "https://api.github.com/graphql";

let token = "5b3718993eb69ba134161325452d177c39d309c6";

let query = {|
  query($first: Int!, $after: String) {
    search(first: $first, after: $after, query: "topic:reasonml", type: REPOSITORY) {
    edges {
      cursor
      node {
        ... on Repository {
          url
          name
          description
          owner {
            login
            avatarUrl
          }
          stargazers {
            totalCount
          }
          languages(first: 1, orderBy: {field: SIZE, direction: DESC}) {
            nodes {
              name
            }
          }
        }
      }
    }
  }
}
|};

let parseLanguages = (languages: array(string)) : option(string) =>
  switch (Array.length(languages)) {
  | 0 => None
  | _ => Some(languages[0])
  };

let parseEdge = json : repo =>
  Json.Decode.{
    cursor: field("cursor", string, json),
    name: at(["node", "name"], string, json),
    url: at(["node", "url"], string, json),
    description: at(["node", "description"], optional(string), json),
    ownerLogin: at(["node", "owner", "login"], string, json),
    ownerAvatarUrl: at(["node", "owner", "avatarUrl"], string, json),
    stars: at(["node", "stargazers", "totalCount"], int, json),
    language:
      at(
        ["node", "languages", "nodes"],
        array(field("name", string)),
        json,
      )
      |> parseLanguages,
  };

let parseData = json : array(repo) =>
  Json.Decode.at(
    ["data", "search", "edges"],
    Json.Decode.array(parseEdge),
    json,
  );

let parseResponse = (text: string) => Js.Json.parseExn(text) |> parseData;

let makeBody = (first: int, after: option(string)) =>
  Json.Encode.object_([
    ("query", Json.Encode.string(query)),
    (
      "variables",
      Json.Encode.object_([
        ("first", Json.Encode.int(first)),
        (
          "after",
          switch (after) {
          | Some(x) => Json.Encode.string(x)
          | None => Json.Encode.null
          },
        ),
      ]),
    ),
  ])
  |> Json.stringify;

let getRepos = (~after, ~first) =>
  Fetch.fetchWithInit(
    url,
    Fetch.RequestInit.make(
      ~method_=Fetch.Post,
      ~body=Fetch.BodyInit.make(makeBody(first, after)),
      ~headers=Fetch.HeadersInit.make({"authorization": "bearer " ++ token}),
      (),
    ),
  )
  |> Js.Promise.then_(res => Fetch.Response.text(res))
  |> Js.Promise.then_(text => Js.Promise.resolve(parseResponse(text)));