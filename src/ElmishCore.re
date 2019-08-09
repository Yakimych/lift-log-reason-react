open AppActions;
open AppReducer;
open ReasonReactElmish;
open Effects;

module Config = {
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
