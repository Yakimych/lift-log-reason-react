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

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(AppReducer.appReducer, InitialState.getInitialState());

  let url = ReasonReactRouter.useUrl();
  let logName = url.path->Belt.List.head->Belt.Option.getWithDefault("");

  let fetchLogEntries = () => {
    dispatch(ApiCallStarted);
    Js.Promise.(
      ApiCaller.fetchLiftLog(logName)
      |> then_(liftLog => dispatch(LogFetchSuccess(liftLog)) |> resolve)
      |> catch(_ => dispatch(ApiCallError("Error fetching log")) |> resolve)
      |> ignore
    );
  };

  let addLogEntry = () => {
    let {newEntryState, dialogState} = state;
    let entry: liftLogEntry = {
      name: newEntryState.name,
      weightLifted: newEntryState.weightLifted,
      date: newEntryState.date,
      sets: dialogState |> Utils.getSetsArray,
      comment: dialogState.comment,
      links: dialogState.links,
    };

    dispatch(ApiCallStarted);
    Js.Promise.(
      ApiCaller.addLogEntry(logName, entry)
      |> then_(_ => fetchLogEntries() |> resolve)
      |> catch(_ => dispatch(ApiCallError("Failed to add entry")) |> resolve)
    )
    |> ignore;
  };

  React.useEffect0(() => {
    fetchLogEntries();
    None;
  });

  <div className="App">
    <header className="App-header">
      <h1 className="App-title">
        {ReasonReact.string(
           state.liftLogState.isLoading
             ? getLoadingText(logName)
             : getHeaderText(
                 logName,
                 state.liftLogState.logTitle,
                 state.liftLogState.networkErrorOccured,
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
            selected={state.newEntryState.date}
            onChange={e => dispatch(ChangeDate(e))}
            className="form-control form-control-sm log-entry-input"
          />
        </div>
        <div className="col">
          <input
            disabled={state.liftLogState.isLoading}
            className="form-control form-control-sm log-entry-input"
            type_="text"
            placeholder="Name"
            maxLength=50
            value={state.newEntryState.name}
            onChange={e =>
              dispatch(ChangeName(ReactEvent.Form.target(e)##value))
            }
          />
        </div>
        <div className="col">
          <input
            disabled={state.liftLogState.isLoading}
            className="form-control form-control-sm log-entry-input"
            type_="text"
            placeholder="Weight"
            value={state.newEntryState.weightLiftedString}
            onChange={e =>
              dispatch(ChangeWeightLifted(ReactEvent.Form.target(e)##value))
            }
          />
        </div>
        <div className="col d-flex align-items-center">
          <span className="mr-2">
            {Utils.formatDialogSetsReps(state.dialogState)
             |> ReasonReact.string}
          </span>
          <Button
            disabled={
              state.liftLogState.isLoading
              || !AppReducer.canAddEntry(state.newEntryState.name)
            }
            size="sm"
            color="primary"
            onClick={_ => dispatch(DialogOpen)}>
            {ReasonReact.string("Add")}
          </Button>
        </div>
      </div>
      <AddReps
        dialogState={state.dialogState}
        onSave={_ => {
          dispatch(DialogClose);
          addLogEntry();
        }}
        closeDialog={_ => dispatch(DialogClose)}
        onInputModeChange={mode => dispatch(SetInputMode(mode))}
        onAddCustomSet={_ => dispatch(AddCustomSet)}
        onRemoveCustomSet={index => dispatch(RemoveCustomSet(index))}
        onCustomSetChange={(index, value) =>
          dispatch(ChangeCustomSet(index, value))
        }
        onNumberOfSetsChange={value => dispatch(SetNumberOfSets(value))}
        onNumberOfRepsChange={value => dispatch(SetNumberOfReps(value))}
        openComment={_ => dispatch(ShowComment)}
        changeComment={value => dispatch(ChangeComment(value))}
        addLink={_ => dispatch(AddLink)}
        removeLink={index => dispatch(RemoveLink(index))}
        changeLinkText={(index, newText) =>
          dispatch(ChangeLinkText(index, newText))
        }
        changeLinkUrl={(index, newUrl) =>
          dispatch(ChangeLinkUrl(index, newUrl))
        }
      />
      <LiftLogContainer entries={state.liftLogState.logEntries} />
    </div>
  </div>;
};
