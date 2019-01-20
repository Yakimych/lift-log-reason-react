open AppState;
open AppActions;
open BsReactstrap;

[%bs.raw
  {|require('./../node_modules/bootstrap/dist/css/bootstrap.min.css')|}
];
[%bs.raw {|require('./AppRoot.css')|}];
[%bs.raw {|require('react-datepicker/dist/react-datepicker.css')|}];

let component = ReasonReact.reducerComponent("AppRoot");

let make = _children => {
  ...component,

  initialState: () => InitialState.getInitialState(),
  reducer: (action, state) => {
    let newState = AppReducer.appReducer(state, action);

    switch (action) {
    | LogFetchStart =>
      ReasonReact.UpdateWithSideEffects(
        newState,
        self => {
          let successAction = liftLog => self.send(LogFetchSuccess(liftLog));
          let errorAction = _ =>
            self.send(LogFetchError("Error fetching log"));
          ApiCaller.fetchLiftLog("testlog", successAction, errorAction);
        },
      )
    | EntryAddStart =>
      ReasonReact.UpdateWithSideEffects(
        newState,
        self => {
          let {newEntryState, dialogState} = self.state;
          let entry: liftLogEntry = {
            name: newEntryState.name,
            weightLifted: newEntryState.weightLifted,
            date: newEntryState.date,
            sets: dialogState.customSets,
          };

          let successAction = _ => self.send(LogFetchStart);
          let errorAction = _ =>
            self.send(EntryAddError("Failed to add entry"));
          ApiCaller.addLogEntry("testlog", entry, successAction, errorAction);
        },
      )
    | _ => ReasonReact.Update(newState)
    };
  },

  didMount: self => self.send(LogFetchStart),
  render: self => {
    let numberOfEntriesText =
      "Number of entries: "
      ++ string_of_int(self.state.liftLogState.logEntries |> List.length);
    <main className="mt-3 mb-3 p-2 box-shadow App-main">
      <span>
        {ReasonReact.string(
           self.state.liftLogState.isLoading ?
             "Loading..." : numberOfEntriesText,
         )}
      </span>
      <div className="add-log-entry">
        <div className="row">
          <div className="col">
            <DatePickerWrapper
              disabled=false
              dateFormat="YYYY-MM-DD"
              selected={self.state.newEntryState.date}
              onChange={e => self.send(ChangeDate(e))}
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
              value={self.state.newEntryState.name}
              onChange={e =>
                self.send(ChangeName(ReactEvent.Form.target(e)##value))
              }
            />
          </div>
          <div className="col">
            <input
              /* disabled={props.disabled} */
              className="form-control form-control-sm log-entry-input"
              type_="text"
              placeholder="Weight"
              value={self.state.newEntryState.weightLiftedString}
              onChange={e =>
                self.send(
                  ChangeWeightLifted(ReactEvent.Form.target(e)##value),
                )
              }
            />
          </div>
          <div className="col d-flex align-items-center">
            /* <span className="mr-2"> {formatRepsSets(props.setsReps)} </span> */
            /* disabled={
                 props.disabled || !canAddEntry(props.name, props.weightLifted)
               } */

              <Button
                size="sm"
                color="primary"
                onClick={_ => self.send(DialogOpen)}>
                {ReasonReact.string("Add")}
              </Button>
            </div>
        </div>
        <AddReps
          dialogState={self.state.dialogState}
          onSave={_ => {
            self.send(DialogClose);
            self.send(EntryAddStart);
          }}
          closeDialog={_ => self.send(DialogClose)}
          onInputModeChange={mode => self.send(SetInputMode(mode))}
          onAddCustomSet={_ => self.send(AddCustomSet)}
          onRemoveCustomSet={index => self.send(RemoveCustomSet(index))}
          onCustomSetChange={(index, value) =>
            self.send(ChangeCustomSet(index, value))
          }
          onNumberOfSetsChange={value => self.send(SetNumberOfSets(value))}
          onNumberOfRepsChange={value => self.send(SetNumberOfReps(value))}
          openComment={_ => self.send(ShowComment)}
          changeComment={value => self.send(ChangeComment(value))}
          addLink={_ => self.send(AddLink)}
          removeLink={index => self.send(RemoveLink(index))}
          changeLinkText={(index, newText) =>
            self.send(ChangeLinkText(index, newText))
          }
          changeLinkUrl={(index, newUrl) =>
            self.send(ChangeLinkUrl(index, newUrl))
          }
        />
        <LiftLogContainer entries={self.state.liftLogState.logEntries} />
      </div>
    </main>;
  },
};
