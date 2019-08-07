[@react.component]
let make = () => {
  let dispatch = ElmishBasic.useDispatch();
  let name = ElmishBasic.useSelector(s => s.name);

  <>
    <div> {ReasonReact.string("NewName: " ++ name)} </div>
    <input
      type_="text"
      value=name
      onChange={e => dispatch(SetName(ReactEvent.Form.target(e)##value))}
    />
  </>;
};
