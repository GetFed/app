// I need to revisit this pattern

const config = {
  local: {
    frontend: "http://localhost:3000",
    api: "http://localhost:5000",
    auth: "http://localhost:4000",
  },
  staging: {
    frontend: "http://tiro-workers.dubcell.com",
    api: "http://api.tiro-workers.dubcell.com",
    auth: "http://auth.tiro-workers.dubcell.com",
  },
  production: {
    frontend: "http://tiro-workers.dubcell.com",
    api: "http://api.tiro-workers.dubcell.com",
    auth: "http://auth.tiro-workers.dubcell.com",
  },
};

const environment = process.env.RAZZLE_APP_ENV || "local";
export default config[environment === "analyze" ? "local" : environment];