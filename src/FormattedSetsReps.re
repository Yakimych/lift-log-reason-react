open AppState;

[@react.component]
let make = () => {
  let dialogState =
    ElmishCore.useSelector(
      React.useCallback0((s: AppState.appState) => s.dialogState),
    );

  <span className="mr-2">
    {Utils.formatDialogSetsReps(
       dialogState.inputMode,
       dialogState.numberOfSets,
       dialogState.numberOfReps,
       dialogState.customSets,
     )
     |> ReasonReact.string}
  </span>;
};
