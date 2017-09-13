open Glamor;

type actions =
  | DownloadRepos (array RepoData.repo)
  | DownloadReposError;

type state = {
  repos: option (array RepoData.repo),
  error: option string
};

let component = ReasonReact.reducerComponent "App";

let style = css [
  display "flex",
  flexDirection "column",
  alignItems "center"
];

let make _children => {
  ...component,
  initialState: fun () => { repos: None, error: None },
  reducer: fun action state =>
    switch action {
    | DownloadRepos repos => ReasonReact.Update { ...state, repos: Some repos }
    | DownloadReposError => ReasonReact.Update {
        ...state,
        error: Some "Encountered error while trying to download repositories"
      }
    },
  didMount: fun { reduce } => {
    RepoData.fetchRepos ()
      |> Js.Promise.then_ (fun repos => {
          reduce (fun () => DownloadRepos repos) ();
          Js.Promise.resolve ();
        })
      |> Js.Promise.catch (fun _ => {
          reduce (fun () => DownloadReposError) ();
          Js.Promise.resolve ();
        })
      |> ignore;

    ReasonReact.NoUpdate;
  },
  render: fun { state } => {
    let element =
      switch (state.repos, state.error) {
      | (Some repos, _) => <RepoList repos=repos />
      | (None, Some error) => ReasonReact.stringToElement error
      | (None, None) => ReasonReact.stringToElement "Loading..."
      };

    <div className=style>
      element
    </div>
  }
};
