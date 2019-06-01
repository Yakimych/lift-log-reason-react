[@bs.module "react-animate-height"] [@react.component]
external make:
  (
    ~duration: int,
    ~className: string,
    ~height: int,
    ~children: React.element
  ) =>
  React.element =
  "default";
