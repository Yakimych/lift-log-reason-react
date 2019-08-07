open AppState;
open AppActions;
open BsReactstrap;

[%bs.raw
  {|require('./../node_modules/bootstrap/dist/css/bootstrap.min.css')|}
];
[%bs.raw {|require('./AppRoot.css')|}];
[%bs.raw {|require('react-datepicker/dist/react-datepicker.css')|}];

let getLoadingText = logName => "Loading " ++ logName;
let getErrorText = logName => "Failed to load: '" ++ logName ++ "'";
let getHeaderText = (logName, logTitle, failedToFetch) =>
  failedToFetch ? getErrorText(logName) : logTitle;

let getLiftLogState = (s: AppState.appState) => s.liftLogState;
let getNewEntryState = (s: AppState.appState) => s.newEntryState;

let getInputMode = (state: appState) => {
  state.dialogState.inputMode;
};
let getNumberOfSets = (state: appState) => {
  state.dialogState.numberOfSets;
};
let getNumberOfReps = (state: appState) => {
  state.dialogState.numberOfReps;
};
let getCustomSets = (state: appState) => {
  state.dialogState.customSets;
};

[@react.component]
let make = () => {
  let dispatch = ElmishTest.useDispatch();
  let liftLogState = ElmishTest.useSelector(getLiftLogState);
  let inputMode = ElmishTest.useSelector(getInputMode);
  let numberOfSets = ElmishTest.useSelector(getNumberOfSets);
  let numberOfReps = ElmishTest.useSelector(getNumberOfReps);
  let customSets = ElmishTest.useSelector(getCustomSets);
  let newEntryState = ElmishTest.useSelector(getNewEntryState);

  let url = ReasonReactRouter.useUrl();
  let logName = url.path->Belt.List.head->Belt.Option.getWithDefault("");

  React.useEffect0(() => {
    dispatch(FetchLogEntries(logName));
    None;
  });

  <div className="App">
    <header className="App-header">
      <h1 className="App-title">
        {ReasonReact.string(
           liftLogState.isLoading
             ? getLoadingText(logName)
             : getHeaderText(
                 logName,
                 liftLogState.logTitle,
                 liftLogState.networkErrorOccured,
               ),
         )}
      </h1>
    </header>
    <div className="mt-3 mb-3 p-2 box-shadow lift-log-container">
      <div className="row">
        <h6 className="col"> {"Date" |> ReasonReact.string} </h6>
        <h6 className="col"> {"Name" |> ReasonReact.string} </h6>
        <h6 className="col"> {"Weight lifted (kg)" |> ReasonReact.string} </h6>
        <h6 className="col"> {"Sets/Reps" |> ReasonReact.string} </h6>
      </div>
      <div className="row">
        <div className="col">
          <DatePickerWrapper
            disabled=false
            dateFormat="YYYY-MM-dd"
            selected={newEntryState.date}
            onChange={e => dispatch(ChangeDate(e))}
            className="form-control form-control-sm log-entry-input"
          />
        </div>
        <div className="col">
          <input
            disabled={liftLogState.isLoading}
            className="form-control form-control-sm log-entry-input"
            type_="text"
            placeholder="Name"
            maxLength=50
            value={newEntryState.name}
            onChange={e =>
              dispatch(ChangeName(ReactEvent.Form.target(e)##value))
            }
          />
        </div>
        <div className="col">
          <input
            disabled={liftLogState.isLoading}
            className="form-control form-control-sm log-entry-input"
            type_="text"
            placeholder="Weight"
            value={newEntryState.weightLiftedString}
            onChange={e =>
              dispatch(ChangeWeightLifted(ReactEvent.Form.target(e)##value))
            }
          />
        </div>
        <div className="col d-flex align-items-center">
          <span className="mr-2">
            {Utils.formatDialogSetsReps(
               inputMode,
               numberOfSets,
               numberOfReps,
               customSets,
             )
             |> ReasonReact.string}
          </span>
          <Button
            disabled={
              liftLogState.isLoading
              || !AppReducer.canAddEntry(newEntryState.name)
            }
            size="sm"
            color="primary"
            onClick={_ => dispatch(DialogOpen)}>
            {ReasonReact.string("Add")}
          </Button>
        </div>
      </div>
      <AddReps logName />
      <LiftLogContainer entries={liftLogState.logEntries} />
    </div>
  </div>;
};
