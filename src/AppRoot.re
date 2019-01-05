open AppState;
open AppActions;
open BsReactstrap;

[%bs.raw
  {|require('./../node_modules/bootstrap/dist/css/bootstrap.min.css')|}
];
[%bs.raw {|require('./AppRoot.css')|}];

let component = ReasonReact.reducerComponent("AppRoot");

let make = (~testProp, _children) => {
  ...component,

  initialState: () => InitialState.getInitialState(),
  reducer: AppReducer.appReducer,

  render: self => {
    let numberOfLinksText =
      "Number of links: "
      ++ string_of_int(self.state.dialogState.links |> List.length);
    <div className="add-log-entry">
      <span> {ReasonReact.string(numberOfLinksText)} </span>
      {self.state.liftLogState.isLoading ?
         ReasonReact.string(testProp) : ReasonReact.null}
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
      <AddReps
        dialogState={self.state.dialogState}
        closeDialog={_ => self.send(DialogClose)}
        changeInputMode={mode => self.send(SetInputMode(mode))}
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
