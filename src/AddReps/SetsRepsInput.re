[@bs.module "@githubprimer/octicons-react"]
external getIconByName: string => 'a = "getIconByName";

[@react.component]
let make =
    (
      ~numberOfSets,
      ~numberOfReps,
      ~onNumberOfSetsChange,
      ~onNumberOfRepsChange,
    ) => {
  <div className="d-flex align-items-center ">
    <input
      className="form-control form-control-sm set-rep-input"
      type_="text"
      value=numberOfSets
      onChange={e => onNumberOfSetsChange(ReactEvent.Form.target(e)##value)}
    />
    <span className="cross-icon-wrapper">
      <OcticonWrapper icon={getIconByName("x")} />
    </span>
    <input
      className="form-control form-control-sm set-rep-input"
      type_="text"
      value=numberOfReps
      onChange={e => onNumberOfRepsChange(ReactEvent.Form.target(e)##value)}
    />
  </div>;
};
