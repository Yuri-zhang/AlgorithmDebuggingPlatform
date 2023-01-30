(function(){"use strict";function u(e,r,t,a){function i(s){const n=c(s),o=[n];return e.isAbsolute(n)||o.unshift(a),e.resolve(...o)}function c(s){const n=process.env.VSCODE_PORTABLE;if(n)return e.join(n,"user-data");let o=process.env.VSCODE_APPDATA;if(o)return e.join(o,t);const f=s["user-data-dir"];if(f)return f;switch(process.platform){case"win32":if(o=process.env.APPDATA,!o){const p=process.env.USERPROFILE;if(typeof p!="string")throw new Error("Windows: Unexpected undefined %USERPROFILE% environment variable");o=e.join(p,"AppData","Roaming")}break;case"darwin":o=e.join(r.homedir(),"Library","Application Support");break;case"linux":o=process.env.XDG_CONFIG_HOME||e.join(r.homedir(),".config");break;default:throw new Error("Platform not supported")}return e.join(o,t)}return{getUserDataPath:i}}if(typeof define=="function")define(["require","path","os","vs/base/common/network","vs/base/common/resources","vs/base/common/process"],function(e,r,t,a,i,c){const s=i.dirname(a.FileAccess.asFileUri("",e)),n=e.__$__nodeRequire(i.joinPath(s,"package.json").fsPath);return u(r,t,n.name,c.cwd())});else if(typeof module=="object"&&typeof module.exports=="object"){const e=require("../../../../../package.json"),r=require("path"),t=require("os");module.exports=u(r,t,e.name,process.env.VSCODE_CWD||process.cwd())}else throw new Error("Unknown context")})();

//# sourceMappingURL=https://ticino.blob.core.windows.net/sourcemaps/da76f93349a72022ca4670c1b84860304616aaa2/core/vs/platform/environment/node/userDataPath.js.map
