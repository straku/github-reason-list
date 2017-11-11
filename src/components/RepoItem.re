let component = ReasonReact.statelessComponent("RepoItem");

let make = (~repo: RepoData.repo, _children) => {
  ...component,
  render: (_self) =>
    <div className="repo-item">
      <a href=repo.htmlUrl> <h2> (ReasonReact.stringToElement(repo.fullName)) </h2> </a>
      (ReasonReact.stringToElement(string_of_int(repo.stargazersCount) ++ " stars"))
    </div>
};
