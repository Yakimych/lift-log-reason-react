open AppState;
open BsReactstrap;

[@react.component]
let make = (~mode: inputMode, ~onChange) => {
  <ButtonGroup>
    <InputModeButton
      id="standardInputModeButton"
      buttonMode=Standard
      currentMode=mode
      onClick=onChange>
      {ReasonReact.string("Standard")}
    </InputModeButton>
    <InputModeButton
      id="customRepsButton"
      buttonMode=Custom
      currentMode=mode
      onClick=onChange>
      {ReasonReact.string("Custom")}
    </InputModeButton>
  </ButtonGroup>;
};
