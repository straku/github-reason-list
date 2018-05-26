open Glamor;

type actions =
  | DownloadRepos(array(Data.repo))
  | DownloadReposError;

type state = {
  repos: option(array(Data.repo)),
  error: option(string),
};

let component = ReasonReact.reducerComponent("App");

let style =
  css([display("flex"), flexDirection("column"), alignItems("center")]);

let make = _children => {
  ...component,
  initialState: () => {repos: None, error: None},
  reducer: (action, state) =>
    switch (action) {
    | DownloadRepos(repos) =>
      ReasonReact.Update({...state, repos: Some(repos)})
    | DownloadReposError =>
      ReasonReact.Update({
        ...state,
        error:
          Some("Encountered error while trying to download repositories"),
      })
    },
  didMount: ({send}) => {
    Data.getRepos(~after=None, ~first=50)
    |> Js.Promise.then_(repos => {
         send(DownloadRepos(repos));
         Js.Promise.resolve();
       })
    |> Js.Promise.catch(_ => {
         send(DownloadReposError);
         Js.Promise.resolve();
       })
    |> ignore;
    ReasonReact.NoUpdate;
  },
  render: ({state}) =>
    <div className=style>
      (
        switch (state.repos, state.error) {
        | (Some(repos), _) => <RepoList repos />
        | (None, Some(error)) => ReasonReact.stringToElement(error)
        | (None, None) => ReasonReact.stringToElement("Loading...")
        }
      )
    </div>,
};