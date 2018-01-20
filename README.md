# GitHub Reason List

Simple app that displays list of GitHub repositories that contains topic "reasonml".

Started by following this tutorial https://jamesfriend.com.au/a-first-reason-react-app-for-js-developers (highly recommended!)

Added (in comparison to tutorial):
- using graphql github api instead of the rest one (not using [graphql_ppx](https://github.com/mhallin/graphql_ppx) yet 😞)
- some styles (using [glamor](https://github.com/poeschko/bs-glamor) bindings), design stolen from GitHub's "Explore this week" newsletter

Want to add:
- lazy loading (by some button at the bottom or infinite scroll)

## Notes

If you want to run it locally you will have to provide your own personal access token here (public_repo scope is enough) https://github.com/straku/github-reason-list/blob/master/src/data.re#L14

There seems to be no way of using github graphql API without the token, so without turning it into full OAuth app with user login through github to get the token I won't be able to provide working online demo, which is a shame 😢
