[@bs.deriving abstract]
type jsProps = {
  disabled: bool,
  dateFormat: string,
  selected: Js.Date.t,
  onChange: Js.Date.t => unit,
  className: string,
};

[@bs.module "react-datepicker"]
external datePickerWrapper: ReasonReact.reactClass = "default";

let make =
    (~disabled, ~dateFormat, ~selected, ~onChange, ~className, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=datePickerWrapper,
    ~props=jsProps(~disabled, ~dateFormat, ~selected, ~onChange, ~className),
    children,
  );
