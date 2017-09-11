open Glamor;

let component = ReasonReact.statelessComponent "Header";

let style = css [
  fontFamily "\"Helvetica Neue\", sans-serif",
  Selector "& > h1" [
    fontSize "40px"
  ]
];

let make _children => {
  ...component,
  render: fun _self => {
    <header className=style>
      <h1>(ReasonReact.stringToElement "Reason projects on GitHub")</h1>
    </header>
  }
}
