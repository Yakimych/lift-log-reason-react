open AppState;
open BsReactstrap;

[@react.component]
let make = (~mode: inputMode, ~onChange) => {
  <ButtonGroup>
    <InputModeButton
      id="standardInputModeButton"
      buttonMode=SetsReps
      currentMode=mode
      onClick=onChange>
      {ReasonReact.string("Standard")}
    </InputModeButton>
    <InputModeButton
      id="customRepsButton"
      buttonMode=CustomReps
      currentMode=mode
      onClick=onChange>
      {ReasonReact.string("Custom")}
    </InputModeButton>
  </ButtonGroup>;
};
