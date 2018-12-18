var path = require('path');
var webpack = require('webpack');

module.exports = function (env) {

    env = env || {};
    var isProd = env.NODE_ENV === 'production';

    // Setup base config for all environments
    var config = {
        entry: {
            main: './main'
        },
        mode: 'none',
        output: {
            path: path.join(__dirname, 'wwwroot/dist'),
            filename: '[name].js'
        },
        devtool: 'eval-source-map',
        resolve: {
            extensions: ['.ts', '.tsx', '.js', '.jsx']
        },
        plugins: [
            new webpack.ProvidePlugin({
                $: 'jquery',
                jQuery: 'jquery'
            })
        ],
        module: {
            rules: [
                { test: /\.css?$/, use: ['style-loader', 'css-loader'] },
                { test: /\.(png|jpg|jpeg|gif|svg)$/, use: 'url-loader?limit=25000' },
                { test: /\.(png|woff|woff2|eot|ttf|svg)(\?|$)/, use: 'url-loader?limit=100000' },
                {
                    test: require.resolve('jquery'),
                    use: [{
                        loader: 'expose-loader',
                        options: '$'
                    }]
                }
            ]
        },
        optimization: {
            minimize: isProd
        }
    }

    // Alter config for prod environment
    if (isProd) {
        config.devtool = '#source-map';
        // config.plugins = config.plugins.concat([
        //     new config.optimization.minimize({
        //         sourceMap: true
        //     })
        // ]);
    }

    return config;
};