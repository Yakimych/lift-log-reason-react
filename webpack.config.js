const path = require("path");
const HtmlWebpackPlugin = require("html-webpack-plugin");
const outputDir = path.join(__dirname, "build/");

console.log("NODE_ENV: ", process.env.NODE_ENV);
console.log("REACT_APP_API_BASE_URL: ", process.env.REACT_APP_API_BASE_URL);

const isProd = process.env.NODE_ENV === "production";
const Dotenv = require("dotenv-webpack");

const cssRegex = /\.css$/;

module.exports = {
  entry: "./src/Index.bs.js",
  mode: isProd ? "production" : "development",
  output: {
    path: outputDir,
    filename: "Index.js"
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: "src/index.html",
      inject: false
    }),
    new Dotenv()
  ],
  devServer: {
    compress: true,
    contentBase: outputDir,
    port: process.env.PORT || 8000,
    historyApiFallback: true
  },
  module: {
    rules: [
      {
        test: cssRegex,
        use: ["style-loader", "css-loader"]
      }
    ]
  }
};
