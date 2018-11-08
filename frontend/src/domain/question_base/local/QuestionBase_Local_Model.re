type _record = {
  editingText: bool,
  editingSolution: bool,
  newAnswerKeyId: Schema.questionAnswerKeyId(Schema.modelIdType),
};

let _defaultRecord = id => {
  module UUIDSeedType = {
    let namespace = id;
  };
  module Rand = UUID.V5Random(UUIDSeedType);
  {
    editingText: true,
    editingSolution: false,
    newAnswerKeyId: `QuestionAnswerKeyId(Rand.generateSeqUUID()),
  };
};

module Record = {
  type t = _record;
  let default = _defaultRecord;
};