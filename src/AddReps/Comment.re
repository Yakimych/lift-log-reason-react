open BsReactstrap;

let linkElementHeight = 40;

[@react.component]
let make =
    (~comment: string, ~hasComment: bool, ~onCommentChange, ~onOpenComment) => {
  <>
    {!hasComment
       ? ReasonReact.null
       : <Button onClick=onOpenComment size="sm">
           {ReasonReact.string("Add comment")}
         </Button>}
    <AnimateHeightWrapper
      duration=350 className="w-100" height={hasComment ? 0 : 62}>
      /* <Fade in_=hasComment unmountOnExit=true> */

        <Input
          /* maxLength=400 */
          _type="textarea"
          value=comment
          onChange={e => onCommentChange(ReactEvent.Form.target(e)##value)}
        />
      </AnimateHeightWrapper>
    /* </Fade> */
  </>;
};
