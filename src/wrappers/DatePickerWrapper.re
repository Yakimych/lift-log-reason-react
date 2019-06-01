[@bs.module "react-datepicker"] [@react.component]
external make:
  (
    ~disabled: bool,
    ~dateFormat: string,
    ~selected: Js.Date.t,
    ~onChange: Js.Date.t => unit,
    ~className: string
  ) =>
  React.element =
  "default";
