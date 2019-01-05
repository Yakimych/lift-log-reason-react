open AppState;
open BsReactstrap;

let component = ReasonReact.statelessComponent("InputModeSwitch");

let make = (~mode: inputMode, ~onChange, _children) => {
  ...component,
  render: _self =>
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
    </ButtonGroup>,
};
