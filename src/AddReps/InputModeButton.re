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
      ~onClick,
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
        id color="primary" size="sm" className onClick outline=true active>
        children
      </Button>
      <Tooltip
        target="tooltipbutton"
        isOpen={self.state.tooltipIsOpen}
        toggle={_ => self.send(ToggleTooltip)}>
        {ReasonReact.string("RPE format: 'Reps@RPE'. E.g. 5@9.5")}
      </Tooltip>
    </>;
  },
};
