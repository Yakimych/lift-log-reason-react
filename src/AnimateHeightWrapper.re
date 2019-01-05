[@bs.deriving abstract]
type jsProps = {
  duration: int,
  className: string,
  height: int,
};

[@bs.module "react-animate-height"]
external animateHeightWrapper: ReasonReact.reactClass = "default";

let make = (~duration, ~className, ~height, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=animateHeightWrapper,
    ~props=jsProps(~duration, ~className, ~height),
    children,
  );
