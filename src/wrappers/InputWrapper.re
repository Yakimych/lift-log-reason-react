[@bs.module "reactstrap"] [@react.component]
external make:
  (
    ~_type: string=?,
    ~maxLength: int=?,
    ~bsSize: string=?,
    ~onChange: ReactEvent.Form.t => unit=?,
    ~value: string=?,
    ~className: string=?,
    unit
  ) =>
  React.element =
  "Input";
