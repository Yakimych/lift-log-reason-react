open AppState;
open AppActions;

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
      <AddReps
        dialogState={self.state.dialogState}
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
