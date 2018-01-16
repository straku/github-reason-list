type repo = {
  fullName: string,
  stargazersCount: int,
  htmlUrl: string
};

let reposUrl = "https://api.github.com/search/repositories?q=topic%3Areasonml&type=Repositories";

let parseRepoJson = json : repo =>
  Json.Decode.{
    fullName: field("full_name", string, json),
    stargazersCount: field("stargazers_count", int, json),
    htmlUrl: field("html_url", string, json)
  };

let parseRepoResponseJson = json : array(repo) =>
  Json.Decode.field("items", Json.Decode.array(parseRepoJson), json);

let fetchRepos = () =>
  Bs_fetch.fetch(reposUrl)
  |> Js.Promise.then_(Bs_fetch.Response.text)
  |> Js.Promise.then_(jsonText =>
       Js.Promise.resolve(parseRepoResponseJson(Js.Json.parseExn(jsonText)))
     );
