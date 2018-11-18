/* Create Fragment Matcher*/
let fragmentMatcher: ApolloInMemoryCache.fragmentMatcher =
  ApolloInMemoryCache.createIntrospectionFragmentMatcher(
    ~data=GraphQLSchema.data,
  );

/* Create an InMemoryCache */
let inMemoryCache: ReasonApolloTypes.apolloCache =
  ApolloInMemoryCache.createInMemoryCache(~fragmentMatcher, ());

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
          ++ (
            Document.isBrowser() ?
              Document.getHash()
              |> LocalStorage.replaceToken(LocalStorage.accessTokenNamespace, _) :
              ""
          )
          |> Json.Encode.string,
        ),
      ]),
    (),
  );

let apiHttpLink = httpLink(Config.config.api ++ "/graphql");
let authHttpLink = httpLink(Config.config.auth);

let apiInstance: ApolloClient.generatedApolloClient =
  ReasonApollo.createApolloClient(
    ~link=apiHttpLink,
    ~cache=inMemoryCache,
    ~ssrMode=!Document.isBrowser(),
    (),
  );

let authInstance: ApolloClient.generatedApolloClient =
  ReasonApollo.createApolloClient(
    ~link=authHttpLink,
    ~cache=inMemoryCache,
    ~ssrMode=!Document.isBrowser(),
    (),
  );
