[@bs.module "@githubprimer/octicons-react"]
external getIconByName: string => 'a = "getIconByName";

let component = ReasonReact.statelessComponent("SetsRepsInput");

let make =
    (
      ~numberOfSets,
      ~numberOfReps,
      ~onNumberOfSetsChange,
      ~onNumberOfRepsChange,
      _children,
    ) => {
  ...component,
  render: _self =>
    <div className="d-flex align-items-center ">
      <input
        className="form-control form-control-sm set-rep-input"
        type_="text"
        value=numberOfSets
        onChange={e =>
          onNumberOfSetsChange(ReactEvent.Form.target(e)##value)
        }
      />
      <span className="cross-icon-wrapper">
        <OcticonWrapper icon={getIconByName("x")} />
      </span>
      <input
        className="form-control form-control-sm set-rep-input"
        type_="text"
        value=numberOfReps
        onChange={e =>
          onNumberOfRepsChange(ReactEvent.Form.target(e)##value)
        }
      />
    </div>,
};
