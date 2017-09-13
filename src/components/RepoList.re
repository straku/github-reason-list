let component = ReasonReact.statelessComponent "RepoList";

let make repos::(repos: array RepoData.repo) _children => {
  ...component,
  render: fun _self =>
    <section>
      <header>
        (ReasonReact.stringToElement "Reason repositories on GitHub")
      </header>
      <ul>
        (ReasonReact.arrayToElement (Array.map
          (fun (repo: RepoData.repo) => <RepoItem key=repo.fullName repo=repo />)
          repos
        ))
      </ul>
    </section>
};
