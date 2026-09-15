import enUS from './en-US.js'
import zhCN from './zh-CN.js'

const messages = { 'zh-CN': zhCN, 'en-US': enUS }

export function translate(locale, key, params = {}) {
  let value = messages[locale]?.[key] ?? messages['zh-CN'][key] ?? key
  for (const [name, replacement] of Object.entries(params)) {
    value = value.replaceAll(`{${name}}`, replacement)
  }
  return value
}
