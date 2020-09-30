// https://reasonml.github.io/reason-react/docs/en/interop
// https://reasonml.github.io/reason-react/docs/en/components#import-from-js
// https://github.com/patternfly/patternfly-react/blob/master/packages/react-core/README.md

[@react.component]
[@bs.module "@patternfly/react-core/dist/umd/react-core.min.js"]
//[@react.component] [@bs.module "react-bootstrap/dist/react-bootstrap.min.js"]
external make: (~variant: string, ~onClick: 'onClick=?, ~children: 'children=?) => React.element =
  "Button";
