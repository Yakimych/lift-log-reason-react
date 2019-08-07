let getName = (model: ElmishBasic.model) => model.name;

[@react.component]
let make = () => {
  let dispatch = ElmishBasic.useDispatch();
  let name = ElmishBasic.useSelector(getName);

  <>
    <div> {ReasonReact.string("NewName: " ++ name)} </div>
    <input
      type_="text"
      value=name
      onChange={e => dispatch(SetName(ReactEvent.Form.target(e)##value))}
    />
  </>;
};
