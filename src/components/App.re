let component = ReasonReact.statelessComponent "App";

let make _children => {
  ...component,
  render: fun _self => {
    let dummyRepo: RepoData.repo = {
      stargazersCount: 27,
      fullName: "dummy-repo-name",
      htmlUrl: "dummy-html-url"
    };

    <div className="app">
      <div className="app__header">
        <h1>(ReasonReact.stringToElement "Reason Projects")</h1>
      </div>
      <RepoItem repo=dummyRepo />
    </div>
  }
}
