open AppState;
open AppActions;

let fetchLogEntries = (logName: string, dispatch: action => unit) => {
  dispatch(ApiCallStarted);
  Js.Promise.(
    ApiCaller.fetchLiftLog(logName)
    |> then_(liftLog => dispatch(LogFetchSuccess(liftLog)) |> resolve)
    |> catch(_ => dispatch(ApiCallError("Error fetching log")) |> resolve)
    |> ignore
  );
  None;
};

let addLogEntry = (state: appState, logName: string, dispatch: action => unit) => {
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
    |> then_(_ => fetchLogEntries(logName, dispatch) |> resolve)
    |> catch(_ =>
         Some(dispatch(ApiCallError("Failed to add entry"))) |> resolve
       )
  )
  |> ignore;
  None;
};
