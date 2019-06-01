open AppState;
open AppActions;
open BsReactstrap;

[%bs.raw
  {|require('./../node_modules/bootstrap/dist/css/bootstrap.min.css')|}
];
[%bs.raw {|require('./AppRoot.css')|}];
[%bs.raw {|require('react-datepicker/dist/react-datepicker.css')|}];

// reducer: (action, state) => {
//   let newState = AppReducer.appReducer(state, action);

//   switch (action) {
//   | FetchLogEntries =>
//     ReasonReact.UpdateWithSideEffects(
//       newState,
//       self => {
//         let successAction = liftLog => self.send(LogFetchSuccess(liftLog));
//         let errorAction = _ =>
//           self.send(ApiCallError("Error fetching log"));
//         ApiCaller.fetchLiftLog("testlog", successAction, errorAction);
//       },
//     )
//   | AddLogEntry =>
//     ReasonReact.UpdateWithSideEffects(
//       newState,
//       self => {
//         let {newEntryState, dialogState} = self.state;
//         let entry: liftLogEntry = {
//           name: newEntryState.name,
//           weightLifted: newEntryState.weightLifted,
//           date: newEntryState.date,
//           sets: dialogState.customSets,
//           comment: dialogState.comment,
//           links: dialogState.links,
//         };

//         let successAction = _ => self.send(FetchLogEntries);
//         let errorAction = _ =>
//           self.send(ApiCallError("Failed to add entry"));
//         ApiCaller.addLogEntry("testlog", entry, successAction, errorAction);
//       },
//     )
//   | _ => ReasonReact.Update(newState)
//   };
// },

// didMount: self => self.send(FetchLogEntries),

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(AppReducer.appReducer, InitialState.getInitialState());

  let numberOfEntriesText =
    "Number of entries: "
    ++ string_of_int(state.liftLogState.logEntries |> List.length);

  <main className="mt-3 mb-3 p-2 box-shadow App-main">
    <span>
      {ReasonReact.string(
         state.liftLogState.isLoading ? "Loading..." : numberOfEntriesText,
       )}
    </span>
    <div className="add-log-entry">
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
            /* disabled={props.disabled} */
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
            /* disabled={props.disabled} */
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
          /* <span className="mr-2"> {formatRepsSets(props.setsReps)} </span> */
          /* disabled={
               props.disabled || !canAddEntry(props.name, props.weightLifted)
             } */

            <Button
              size="sm" color="primary" onClick={_ => dispatch(DialogOpen)}>
              {ReasonReact.string("Add")}
            </Button>
          </div>
      </div>
      <AddReps
        dialogState={state.dialogState}
        onSave={_ => {
          dispatch(DialogClose);
          dispatch(AddLogEntry);
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
  </main>;
};
