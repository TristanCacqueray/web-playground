// A simple about modal
[@react.component]
let make = () => {
  let (isOpen, setState) = React.useState(_ => false);
  <>
    <Button variant="regular" onClick={_ => setState(_ => true)}>
      {"About" |> React.string}
    </Button>
    <AboutModal
      isOpen
      onClose={_ => setState(_ => false)}
      productName="test"
      brandImageAlt="Patternfly Logo">
      <TextContent>
        <TextList component="dl">
          <TextListItem component="dt">
            {"Hello" |> React.string}
          </TextListItem>
        </TextList>
      </TextContent>
    </AboutModal>
  </>;
};
