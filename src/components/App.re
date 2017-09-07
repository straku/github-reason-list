type componentState = {
  repos: option (array RepoData.repo)
};

let component = ReasonReact.statefulComponent "App";

let handleReposLoaded repos _self => {
  ReasonReact.Update {
    repos: Some repos
  };
};

let make _children => {
  ...component,
  initialState: fun () => {
    repos: None
  },
  didMount: fun self => {
    RepoData.fetchRepos ()
      |> Js.Promise.then_ (fun repos => {
          (self.update handleReposLoaded) repos;
          Js.Promise.resolve ();
        })
      |> ignore;

    ReasonReact.NoUpdate;
  },
  render: fun { state } => {
    let repoItem =
      switch (state.repos) {
      | Some repos => ReasonReact.arrayToElement (Array.map
          (fun (repo: RepoData.repo) => <RepoItem key=repo.fullName repo=repo />)
          repos
        );
      | None => ReasonReact.stringToElement "Loading"
      };

    <div className="app">
      <div className="app__header">
        <h1>(ReasonReact.stringToElement "Reason Projects")</h1>
      </div>
      repoItem
    </div>
  }
};
