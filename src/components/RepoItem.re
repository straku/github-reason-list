let component = ReasonReact.statelessComponent "RepoItem";

let make repo::(repo: RepoData.repo) _children => {
  ...component,
  render: fun _self => {
    <div className="repo-item">
      <a href=repo.htmlUrl>
        <h2>(ReasonReact.stringToElement repo.fullName)</h2>
      </a>
      (ReasonReact.stringToElement (string_of_int repo.stargazersCount ^ " stars"))
    </div>
  }
}
