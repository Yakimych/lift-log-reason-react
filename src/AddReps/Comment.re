open BsReactstrap;

let linkElementHeight = 40;

[@react.component]
let make =
    (~comment: string, ~hasComment: bool, ~onCommentChange, ~onOpenComment) => {
  <>
    {hasComment
       ? ReasonReact.null
       : <Button onClick=onOpenComment size="sm">
           {ReasonReact.string("Add comment")}
         </Button>}
    <AnimateHeightWrapper
      duration=350
      className="w-100"
      height={hasComment ? [%raw "\"auto\""] : 0}>
      <FadeWrapper _in=hasComment unmountOnExit=true>
        <InputWrapper
          maxLength=400
          _type="textarea"
          value=comment
          onChange={e => onCommentChange(ReactEvent.Form.target(e)##value)}
        />
      </FadeWrapper>
    </AnimateHeightWrapper>
  </>;
};
