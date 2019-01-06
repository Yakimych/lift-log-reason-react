open AppState;
open AppActions;
open BsReactstrap;

[%bs.raw
  {|require('./../node_modules/bootstrap/dist/css/bootstrap.min.css')|}
];
[%bs.raw {|require('./AppRoot.css')|}];
[%bs.raw {|require('react-datepicker/dist/react-datepicker.css')|}];

module Decode = {
  let set = json => {
    open! Json.Decode;
    {
      reps: json |> field("numberOfReps", int),
      rpe: json |> field("rpe", optional(float)),
    };
  };
  let logEntry = json => {
    open! Json.Decode;
    {
      name: json |> field("name", string),
      weightLifted: json |> field("weightLifted", float),
      date: json |> field("date", date),
      sets: json |> field("sets", list(set)),
    };
  };
  let liftLog = json =>
    Json.Decode.{
      name: json |> field("name", string),
      title: json |> field("title", string),
      entries: json |> field("entries", list(logEntry)),
    };
};

let component = ReasonReact.reducerComponent("AppRoot");

let make = (~testProp, _children) => {
  ...component,

  initialState: () => InitialState.getInitialState(),
  reducer: (action, state) =>
    switch (action) {
    | LogFetchStart =>
      ReasonReact.UpdateWithSideEffects(
        {
          ...state,
          liftLogState: {
            ...state.liftLogState,
            isLoading: true,
          },
        },
        self =>
          Js.Promise.(
            Axios.get("http://localhost:5000/api/LiftLogs/testlog")
            |> then_(response =>
                 response##data
                 |> Decode.liftLog
                 |> (liftLog => self.send(LogFetchSuccess(liftLog)))
                 |> resolve
               )
            |> catch(error => resolve(Js.log(error)))
            |> ignore
          ),
      )
    | otherAction => AppReducer.appReducer(otherAction, state)
    },

  didMount: self => self.send(LogFetchStart),
  render: self => {
    let numberOfLinksText =
      "Number of entries: "
      ++ string_of_int(self.state.liftLogState.logEntries |> List.length);
    <div className="add-log-entry">
      <span> {ReasonReact.string(numberOfLinksText)} </span>
      {self.state.liftLogState.isLoading ?
         ReasonReact.string(testProp) : ReasonReact.null}
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
              size="sm" color="primary" onClick={_ => self.send(DialogOpen)}>
              {ReasonReact.string("Add")}
            </Button>
          </div>
      </div>
      <AddReps
        dialogState={self.state.dialogState}
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
    </div>;
  },
};
