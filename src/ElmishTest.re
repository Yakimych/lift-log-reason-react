open AppActions;
open AppState;
open AppReducer;
open ReasonReactElmish;

module Config = {
  let fetchLogEntries = (logName: string, dispatch: AppActions.action => unit) => {
    dispatch(ApiCallStarted);
    Js.Promise.(
      ApiCaller.fetchLiftLog(logName)
      |> then_(liftLog => dispatch(LogFetchSuccess(liftLog)) |> resolve)
      |> catch(_ => dispatch(ApiCallError("Error fetching log")) |> resolve)
      |> ignore
    );
    None;
  };

  let addLogEntry =
      (state: appState, logName: string, dispatch: AppActions.action => unit) => {
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

  let update = (model, message) => {
    let result = appReducer(model, message);

    switch (message) {
    | FetchLogEntries(logName) => (result, Some(fetchLogEntries(logName)))
    | ConfirmAddEntry(logName) => (
        result,
        Some(addLogEntry(model, logName)),
      )
    | _ => (result, None)
    };
  };

  let initialState = (InitialState.getInitialState(), None);
};

include Elmish.Make({
  type model = AppState.appState;

  type message = AppActions.action;

  let update = Config.update;
  let storeEnhancer = None;
  let initialState = Config.initialState;
});
