open Glamor;

let s = ReasonReact.stringToElement;

let component = ReasonReact.statelessComponent("RepoList");

let linkStyle =
  css([color("black"), fontWeight("600"), textDecoration("none")]);

let make = (~repos: array(Data.repo), _children) => {
  ...component,
  render: _self =>
    <section>
      <header className=(css([fontSize("32px"), padding("20px 0")]))>
        <a href="https://reasonml.github.io/" className=linkStyle>
          (s("Reason"))
        </a>
        (s(" repositories on "))
        <a href="https://github.com/" className=linkStyle> (s("GitHub")) </a>
      </header>
      <ul className=(css([listStyle("none"), padding("0")]))>
        (
          ReasonReact.arrayToElement(
            Array.map(
              (repo: Data.repo) => <RepoItem key=repo.cursor repo />,
              repos
            )
          )
        )
      </ul>
    </section>
};