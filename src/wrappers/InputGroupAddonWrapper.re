[@bs.module "reactstrap"] [@react.component]
external make:
  (
    ~tag: 'a=?,
    ~addonType: 'a,
    ~className: string=?,
    ~cssModule: 'd=?,
    ~children: React.element=?,
    unit
  ) =>
  React.element =
  "InputGroupAddon";
