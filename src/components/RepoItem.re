open Glamor;

let s = ReasonReact.stringToElement;

let component = ReasonReact.statelessComponent("RepoItem");

let make = (~repo: Data.repo, _children) => {
  ...component,
  render: _self =>
    <li
      className=(
        css([
          fontSize("14px"),
          color("#6f6f6f"),
          padding("20px 4px"),
          borderStyle("solid"),
          borderWidth("1px 0 0"),
          borderColor("#eaecef")
        ])
      )>
      <a
        href=repo.url
        className=(
          css([
            display("flex"),
            alignItems("center"),
            color("#0366d6"),
            textDecoration("none"),
            fontSize("18px"),
            fontWeight("600"),
            marginBottom("16px")
          ])
        )>
        <img
          src=repo.ownerAvatarUrl
          className=(css([width("36px"), height("36px"), marginRight("16px")]))
        />
        (s(repo.ownerLogin ++ " / " ++ repo.name))
      </a>
      <div className=(css([marginBottom("10px")]))>
        (
          switch repo.description {
          | Some(desc) => s(desc)
          | None => ReasonReact.nullElement
          }
        )
      </div>
      <div className=(css([display("flex"), alignItems("center")]))>
        <div className=(css([width("85px")]))>
          (s({js|★ |js} ++ string_of_int(repo.stars)))
        </div>
        <div>
          (
            switch repo.language {
            | Some(lang) => s(lang)
            | None => ReasonReact.nullElement
            }
          )
        </div>
      </div>
    </li>
};