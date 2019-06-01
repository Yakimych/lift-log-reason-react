open AppState;
open BsReactstrap;

[@react.component]
let make =
    (
      ~id: string,
      ~buttonMode: inputMode,
      ~currentMode: inputMode,
      ~onClick: inputMode => unit,
      ~children,
    ) => {
  let (tooltipIsOpen, setToolTipIsOpen) = React.useState(() => false);
  let toggleTooltip = () => setToolTipIsOpen(isOpen => !isOpen);

  let active = buttonMode == currentMode;
  let className = active ? "" : "btn-primary--lighter";
  <>
    <Button
      id
      color="primary"
      size="sm"
      className
      onClick={_ => onClick(buttonMode)}
      outline=true
      active>
      children
    </Button>
    <Tooltip
      target="customRepsButton" isOpen=tooltipIsOpen toggle=toggleTooltip>
      {ReasonReact.string("RPE format: 'Reps@RPE'. E.g. 5@9.5")}
    </Tooltip>
  </>;
};
