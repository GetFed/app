/* Create Fragment Matcher*/
let fragmentMatcher: ApolloInMemoryCache.fragmentMatcher =
  ApolloInMemoryCache.createIntrospectionFragmentMatcher(
    ~data=GraphQLSchema.data,
  );

/* Create an InMemoryCache */
let inMemoryCache: ReasonApolloTypes.apolloCache =
  ApolloInMemoryCache.createInMemoryCache(~fragmentMatcher, ());

let authInMemoryCache: ReasonApolloTypes.apolloCache =
  ApolloInMemoryCache.createInMemoryCache();


let getToken = () =>
  Document.isBrowser() ?
    LocalStorage.accessTokenNamespace
    |> LocalStorage.getAuth
    |> Belt.Option.getWithDefault(_, "") :
    "";

/* create context link*/
let headerContextLink = ApolloLinks.createContextLink(() => {
  let token = getToken();
  Js.log("headerContextLink = token " );
  Js.log(token);
  {
    "headers": {
      "authorization": "Bearer " ++ token,
      "accounts-access-token": token
    }
  }
});

/* Create an HTTP Link */
let httpLink = (url: string): ReasonApolloTypes.apolloLink => 
  ApolloLinks.createHttpLink(
    ~uri=(url),
    ~fetch=Document.isBrowser() ? Document.fetch : Node.fetch,
    ~headers=
      Json.Encode.object_([
        (
          "authorization",
          "Bearer "
          ++ (Document.isBrowser() ? getToken() : "")
          |> Json.Encode.string,
        ),
      ]),
    (),
  );

let apiHttpLink = httpLink(Config.config.api ++ "/graphql");
let authHttpLink = httpLink(Config.config.auth);

let apiInstance: ApolloClient.generatedApolloClient =
  ReasonApollo.createApolloClient(
    ~link=ApolloLinks.from([|headerContextLink, apiHttpLink|]),
    ~cache=inMemoryCache,
    ~ssrMode=!Document.isBrowser(),
    (),
  );

let authInstance: ApolloClient.generatedApolloClient =
  ReasonApollo.createApolloClient(
    ~link=ApolloLinks.from([|headerContextLink, authHttpLink|]),
    ~cache=authInMemoryCache,
    ~ssrMode=!Document.isBrowser(),
    ~queryDeduplication=false,
    (),
  );
