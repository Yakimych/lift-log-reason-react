open AppState;
open BsReactstrap;

type state = {tooltipIsOpen: bool};

type action =
  | ToggleTooltip;

let component = ReasonReact.reducerComponent("InputModeButton");

let make =
    (
      ~id: string,
      ~buttonMode: inputMode,
      ~currentMode: inputMode,
      ~onClick: inputMode => unit,
      children,
    ) => {
  ...component,

  initialState: () => {tooltipIsOpen: false},
  reducer: (action, state) =>
    switch (action) {
    | ToggleTooltip =>
      ReasonReact.Update({tooltipIsOpen: !state.tooltipIsOpen})
    },

  render: self => {
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
        target="customRepsButton"
        isOpen={self.state.tooltipIsOpen}
        toggle={_ => self.send(ToggleTooltip)}>
        {ReasonReact.string("RPE format: 'Reps@RPE'. E.g. 5@9.5")}
      </Tooltip>
    </>;
  },
};
