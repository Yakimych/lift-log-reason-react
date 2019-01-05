[@bs.deriving abstract]
type jsProps = {icon: string};

[@bs.module "@githubprimer/octicons-react"]
external octiconWrapper: ReasonReact.reactClass = "default";

let make = (~icon, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=octiconWrapper,
    ~props=jsProps(~icon),
    children,
  );
