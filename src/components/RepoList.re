let component = ReasonReact.statelessComponent("RepoList");

let make = (~repos: array(RepoData.repo), _children) => {
  ...component,
  render: (_self) =>
    <section>
      <header> (ReasonReact.stringToElement("Reason repositories on GitHub")) </header>
      <ul>
        (
          ReasonReact.arrayToElement(
            Array.map((repo: RepoData.repo) => <RepoItem key=repo.fullName repo />, repos)
          )
        )
      </ul>
    </section>
};
