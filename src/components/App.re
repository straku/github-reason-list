open Glamor;

type actions =
  | DownloadRepos(array(RepoData.repo))
  | DownloadReposError;

type state = {
  repos: option(array(RepoData.repo)),
  error: option(string)
};

let component = ReasonReact.reducerComponent("App");

let style = css([display("flex"), flexDirection("column"), alignItems("center")]);

let make = (_children) => {
  ...component,
  initialState: () => {repos: None, error: None},
  reducer: (action, state) =>
    switch action {
    | DownloadRepos(repos) => ReasonReact.Update({...state, repos: Some(repos)})
    | DownloadReposError =>
      ReasonReact.Update({
        ...state,
        error: Some("Encountered error while trying to download repositories")
      })
    },
  didMount: ({reduce}) => {
    RepoData.fetchRepos()
    |> Js.Promise.then_(
         (repos) => {
           reduce(() => DownloadRepos(repos), ());
           Js.Promise.resolve()
         }
       )
    |> Js.Promise.catch(
         (_) => {
           reduce(() => DownloadReposError, ());
           Js.Promise.resolve()
         }
       )
    |> ignore;
    ReasonReact.NoUpdate
  },
  render: ({state}) => {
    let element =
      switch (state.repos, state.error) {
      | (Some(repos), _) => <RepoList repos />
      | (None, Some(error)) => ReasonReact.stringToElement(error)
      | (None, None) => ReasonReact.stringToElement("Loading...")
      };
    <div className=style> element </div>
  }
};