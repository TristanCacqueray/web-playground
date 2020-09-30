// https://www.patternfly.org/v4/components/about-modal/react/#props
[@react.component]
[@bs.module "@patternfly/react-core/dist/umd/react-core.min.js"]
external make: (~isOpen: bool, ~productName: string, ~brandImageAlt: string, ~onClose: 'onCllose=?, ~children: 'children=?) => React.element =
  "AboutModal";
