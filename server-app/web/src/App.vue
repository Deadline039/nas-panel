<script setup>
import { computed, onBeforeUnmount, onMounted, reactive, ref, watch } from 'vue'

import { translate } from './i18n/index.js'


const storedLocale = window.localStorage.getItem('nas-panel-locale')
const locale = ref(storedLocale === 'en-US' ? 'en-US' : 'zh-CN')
const storedTheme = window.localStorage.getItem('nas-panel-theme')
const theme = ref(storedTheme === 'light' ? 'light' : 'dark')
const activePage = ref('overview')
const status = ref(null)
const loadError = ref('')
const saving = ref(false)
const saved = ref(false)
const formError = ref('')
const activeFanCurve = ref('cpu')
const fanDragging = ref(false)
const defaultFanCurve = [0, 0, 0, 0, 0, 0, 0, 30, 40, 50, 60, 70, 80, 90, 100, 100, 100, 100, 100, 100]
const form = reactive({
  listen: ':8080', panelSerial: '', serverVersion: '', publicScheme: 'http', publicPort: 8080, basePath: '', links: [],
  fanCurves: { cpu: [...defaultFanCurve], hdd: [...defaultFanCurve] },
})
let refreshTimer
let formInitialized = false
const pageBase = window.location.pathname.endsWith('/') ? window.location.pathname.slice(0, -1) : window.location.pathname

function t(key, params = {}) { return translate(locale.value, key, params) }

const pages = computed(() => [
  { id: 'overview', label: t('overview'), description: t('overviewDesc') },
  { id: 'network', label: t('network'), description: t('networkDesc') },
  { id: 'storage', label: t('storage'), description: t('storageDesc') },
  { id: 'system', label: t('system'), description: t('systemDesc') },
  { id: 'about', label: t('about'), description: t('aboutDesc') },
  { id: 'fans', label: t('fans'), description: t('fansDesc') },
  { id: 'settings', label: t('settings'), description: t('settingsDesc') },
])
const activeMeta = computed(() => pages.value.find((page) => page.id === activePage.value) ?? pages.value[0])
const system = computed(() => status.value?.system ?? {})
const panel = computed(() => status.value?.panel ?? {})
const energy = computed(() => status.value?.energy ?? {})
const report = computed(() => panel.value.latestReport ?? {})
const power = computed(() => (Number(report.value.voltage || 0) * Number(report.value.current || 0)).toFixed(2))
const automaticURLs = computed(() => (system.value.networks ?? [])
  .filter((network) => network.status === 2 && network.ipAddress)
  .map((network) => ({ name: network.name, url: `${form.publicScheme}://${network.ipAddress}:${form.publicPort}${form.basePath ? `${form.basePath}/` : ''}` })))
const allURLs = computed(() => [
  ...automaticURLs.value.map((link) => ({ ...link, kind: t('automatic') })),
  ...form.links.map((link) => ({ ...link, kind: t('custom') })),
])

async function loadStatus(copySettings = false) {
  try {
    const response = await fetch(`${pageBase}/api/v1/status`, { cache: 'no-store' })
    if (response.ok === false) throw new Error(`HTTP ${response.status}`)
    const data = await response.json()
    status.value = data
    loadError.value = ''
    if (copySettings || formInitialized === false) {
      Object.assign(form, cloneConfig(data.settings))
      formInitialized = true
    }
  } catch (error) {
    loadError.value = error.message
  }
}

async function saveConfig() {
  saving.value = true
  saved.value = false
  formError.value = ''
  try {
    const response = await fetch(`${pageBase}/api/v1/config`, { method: 'PUT', headers: { 'Content-Type': 'application/json' }, body: JSON.stringify(form) })
    const data = await response.json()
    if (response.ok === false) throw new Error(data.error || `HTTP ${response.status}`)
    Object.assign(form, cloneConfig(data))
    saved.value = true
    await loadStatus()
    window.setTimeout(() => { saved.value = false }, 2500)
  } catch (error) {
    formError.value = error.message
  } finally {
    saving.value = false
  }
}

function normalizeFanCurve(curve) {
  return Array.from({ length: 20 }, (_, index) => Math.max(0, Math.min(100, Number(curve?.[index] ?? defaultFanCurve[index]))))
}

function cloneConfig(config) {
  return {
    ...config,
    links: (config?.links ?? []).map((link) => ({ ...link })),
    fanCurves: {
      cpu: normalizeFanCurve(config?.fanCurves?.cpu),
      hdd: normalizeFanCurve(config?.fanCurves?.hdd),
    },
  }
}
function addLink() { form.links.push({ name: `Link ${form.links.length + 1}`, url: 'https://' }) }
function removeLink(index) { form.links.splice(index, 1) }
function toggleTheme() { theme.value = theme.value === 'dark' ? 'light' : 'dark' }

function fanPointX(index) { return 40 + (940 * index / 19) }
function fanPointY(value) { return 220 - Math.max(0, Math.min(100, Number(value))) * 2 }
function fanCurvePoints(name) { return form.fanCurves[name].map((value, index) => `${fanPointX(index)},${fanPointY(value)}`).join(' ') }
function fanTemperatureLabel(index) { return index === 19 ? '95–100℃' : `${index * 5}℃` }
function setFanValue(name, index, value) { form.fanCurves[name][index] = Math.round(Math.max(0, Math.min(100, Number(value) || 0))) }

function updateFanFromPointer(event) {
  if (fanDragging.value === false) return
  const bounds = event.currentTarget.getBoundingClientRect()
  const x = (event.clientX - bounds.left) * 1000 / bounds.width
  const y = (event.clientY - bounds.top) * 260 / bounds.height
  const index = Math.max(0, Math.min(19, Math.round((x - 40) * 19 / 940)))
  setFanValue(activeFanCurve.value, index, (220 - y) / 2)
}

function beginFanDrag(event) {
  fanDragging.value = true
  event.currentTarget.setPointerCapture(event.pointerId)
  updateFanFromPointer(event)
}

function endFanDrag(event) {
  fanDragging.value = false
  if (event.currentTarget.hasPointerCapture(event.pointerId)) event.currentTarget.releasePointerCapture(event.pointerId)
}

function formatBytes(bytes) {
  let value = Number(bytes || 0)
  const units = ['B', 'KB', 'MB', 'GB', 'TB']
  let unit = 0
  while (value >= 1024 && unit < units.length - 1) { value /= 1024; unit++ }
  return `${value.toFixed(unit < 2 ? 0 : 1)} ${units[unit]}`
}

function formatKB(value, rate = false) {
  let scaled = Number(value || 0)
  const units = ['KB', 'MB', 'GB', 'TB']
  let unit = 0
  while (scaled >= 1024 && unit < units.length - 1) { scaled /= 1024; unit++ }
  return `${scaled.toFixed(1)} ${units[unit]}${rate ? '/s' : ''}`
}

function formatUptime(minutes) {
  const value = Number(minutes || 0)
  if (value > 1440) return `${Math.round(value / 1440)} d`
  if (value > 60) return `${Math.round(value / 60)} h`
  return `${value} min`
}

function formatEnergy(kilowattHours) { return Number(kilowattHours || 0).toFixed(4) }

function formatTime(value) {
  if (!value || value.startsWith('0001-')) return t('neverReceived')
  return new Intl.DateTimeFormat(locale.value, { dateStyle: 'short', timeStyle: 'medium' }).format(new Date(value))
}

function networkState(value) { return [t('disconnected'), t('acquiring'), t('connected')][value] ?? t('unknown') }
function diskState(value) { return [t('diskGood'), t('diskWarning'), t('diskFailure')][value] ?? t('unknown') }
function pageName(value) { return pages.value[value]?.label ?? t('unknown') }
function byteLength(value) { return new TextEncoder().encode(value ?? '').length }
function temperatureClass(value) { return Number(value) >= 85 ? 'bad' : Number(value) >= 50 ? 'warn' : 'good' }
function usageClass(value) { return Number(value) >= 90 ? 'bad-progress' : Number(value) >= 75 ? 'warn-progress' : '' }

watch(theme, (value) => {
  document.documentElement.dataset.theme = value
  window.localStorage.setItem('nas-panel-theme', value)
}, { immediate: true })
watch(locale, (value) => {
  document.documentElement.lang = value
  window.localStorage.setItem('nas-panel-locale', value)
}, { immediate: true })

onMounted(() => {
  loadStatus(true)
  refreshTimer = window.setInterval(loadStatus, 2000)
})
onBeforeUnmount(() => window.clearInterval(refreshTimer))
</script>

<template>
  <div class="app-shell">
    <aside class="sidebar">
      <div class="brand"><div class="brand-mark"><span></span><span></span><span></span></div><h1>NAS Panel</h1></div>
      <nav class="page-tabs" :aria-label="t('page')">
        <button v-for="page in pages" :key="page.id" :class="{ active: activePage === page.id }" @click="activePage = page.id"><strong>{{ page.label }}</strong></button>
      </nav>
      <div class="sidebar-footer">
        <div class="connection" :class="{ online: panel.connected }"><i></i><span>{{ panel.connected ? t('panelOnline') : t('waitingPanel') }}</span></div>
        <div class="sidebar-controls">
          <label><span>{{ t('language') }}</span><select v-model="locale"><option value="zh-CN">中文</option><option value="en-US">English</option></select></label>
          <button class="theme-toggle" :aria-label="t('theme')" @click="toggleTheme"><span>{{ theme === 'dark' ? '☾' : '☀' }}</span>{{ theme === 'dark' ? t('darkTheme') : t('lightTheme') }}</button>
        </div>
      </div>
    </aside>

    <main class="workspace">
      <header class="page-header"><div><h2>{{ activeMeta.label }}</h2><span>{{ activeMeta.description }}</span></div><div class="live-time"><span>{{ t('lastUpdate') }}</span><strong>{{ status?.system?.updatedAt ? formatTime(status.system.updatedAt) : '--' }}</strong></div></header>
      <div v-if="loadError" class="alert">{{ t('connectionError', { message: loadError }) }}</div>

      <section v-if="activePage === 'overview'" class="page-content">
        <div class="overview-lead panel-card"><div class="host-summary"><h3>{{ system.hostname || 'LOCAL NAS' }}</h3><strong>{{ system.osName || '--' }}</strong><span>{{ system.cpuName || '--' }}</span></div><div class="load-ring" :style="{ '--load': `${system.cpuLoad || 0}%` }"><div><strong>{{ system.cpuLoad || 0 }}</strong><span>% CPU</span></div></div></div>
        <div class="metric-grid">
          <article class="metric-card blue"><span>{{ t('runtime') }}</span><strong>{{ formatUptime(system.runningMinutes) }}</strong></article>
          <article class="metric-card violet"><span>{{ t('memoryLoad') }}</span><strong>{{ system.memoryLoad || 0 }}%</strong><small>{{ system.memoryName || '--' }}</small></article>
          <article class="metric-card amber"><span>{{ t('cpuTemperature') }}</span><strong :class="temperatureClass(system.cpuTemperature)">{{ system.cpuTemperature || 0 }}℃</strong></article>
          <article class="metric-card green"><span>{{ t('diskTemperature') }}</span><strong :class="temperatureClass(system.hddTemperature)">{{ system.hddTemperature || 0 }}℃</strong><small>{{ t('physicalDisks', { count: system.disks?.length || 0 }) }}</small></article>
        </div>
        <div class="energy-grid">
          <article class="panel-card energy-card"><h3>{{ t('bootEnergy') }}</h3><strong>{{ formatEnergy(energy.bootKWh) }} <small>{{ t('energyUnit') }}</small></strong></article>
          <article class="panel-card energy-card"><h3>{{ t('totalEnergy') }}</h3><strong>{{ formatEnergy(energy.totalKWh) }} <small>{{ t('energyUnit') }}</small></strong></article>
        </div>
        <article class="panel-card telemetry-card"><div class="section-head"><h3>{{ t('panelTelemetry') }}</h3><code>{{ panel.serial || '3939:0831' }}</code></div><div class="electrical-grid"><div><span>{{ t('voltage') }}</span><strong>{{ Number(report.voltage || 0).toFixed(2) }}</strong><small>V</small></div><div><span>{{ t('current') }}</span><strong>{{ Number(report.current || 0).toFixed(2) }}</strong><small>A</small></div><div><span>{{ t('power') }}</span><strong>{{ power }}</strong><small>W</small></div></div><div class="fan-grid"><div><span>{{ t('cpuFan') }}</span><b>{{ report.cpuFanSpeed || 0 }}%</b><progress max="100" :value="report.cpuFanSpeed || 0"></progress></div><div><span>{{ t('hddFan') }}</span><b>{{ report.hddFanSpeed || 0 }}%</b><progress max="100" :value="report.hddFanSpeed || 0"></progress></div></div><footer><span>{{ t('responses', { count: panel.responses || 0 }) }}</span><span>{{ formatTime(panel.lastSeen) }}</span></footer></article>
      </section>

      <section v-else-if="activePage === 'network'" class="page-content"><article class="panel-card table-card"><div class="section-head"><h3>{{ t('network') }}</h3><code>{{ t('physicalInterfaces', { count: system.networks?.length || 0 }) }}</code></div><div class="table-wrap"><table><thead><tr><th>{{ t('interface') }}</th><th>{{ t('state') }}</th><th>{{ t('address') }}</th><th>{{ t('netmask') }}</th><th>{{ t('gateway') }}</th><th>{{ t('upload') }}</th><th>{{ t('download') }}</th><th>{{ t('totalTraffic') }}</th></tr></thead><tbody><tr v-for="network in system.networks" :key="network.name"><td><b>{{ network.name }}</b></td><td><span class="state" :class="`state-${network.status}`"><i></i>{{ networkState(network.status) }}</span></td><td>{{ network.ipAddress || '--' }}</td><td>{{ network.netmask || '--' }}</td><td>{{ network.gateway || '--' }}</td><td>{{ formatKB(network.uploadRateKB, true) }}</td><td>{{ formatKB(network.downloadRateKB, true) }}</td><td>{{ formatKB(network.uploadTotalKB + network.downloadTotalKB) }}</td></tr><tr v-if="!system.networks?.length"><td colspan="8" class="empty">{{ t('noNetwork') }}</td></tr></tbody></table></div></article></section>

      <section v-else-if="activePage === 'storage'" class="page-content">
        <article class="panel-card table-card">
          <div class="section-head"><h3>{{ t('storage') }}</h3><code>{{ t('physicalDisks', { count: system.disks?.length || 0 }) }}</code></div>
          <div class="table-wrap"><table><thead><tr><th>{{ t('device') }}</th><th>{{ t('mountpoint') }}</th><th>{{ t('capacity') }}</th><th>{{ t('usage') }}</th><th>{{ t('health') }}</th><th>{{ t('temperature') }}</th><th>{{ t('powerOnHours') }}</th><th>{{ t('cycles') }}</th></tr></thead><tbody>
            <tr v-for="disk in system.disks" :key="disk.path"><td><b>{{ disk.path }}</b></td><td>{{ disk.mountpoint || '--' }}</td><td>{{ formatBytes(disk.capacity) }}</td><td><div class="usage-cell"><span>{{ disk.usedPercent }}%</span><progress max="100" :value="disk.usedPercent" :class="usageClass(disk.usedPercent)"></progress></div></td><td><span :class="disk.status === 0 ? 'good' : disk.status === 1 ? 'warn' : 'bad'">{{ diskState(disk.status) }}</span></td><td><span :class="temperatureClass(disk.temperature)">{{ disk.temperature }}℃</span></td><td>{{ t('hours', { count: disk.powerOnHours }) }}</td><td>{{ t('cycleCount', { count: disk.cycles }) }}</td></tr>
            <tr v-if="!system.disks?.length"><td colspan="8" class="empty">{{ t('noStorage') }}</td></tr>
          </tbody></table></div>
        </article>
      </section>

      <section v-else-if="activePage === 'fans'" class="page-content">
        <article class="panel-card fan-curve-card">
          <div class="section-head"><div><h3>{{ t('fanCurve') }}</h3><span>{{ t('fanCurveHint') }}</span></div><div class="fan-actions"><span v-if="panel.fanCurvePending" class="state state-1"><i></i>{{ t('waitingDelivery') }}</span><button class="primary" :disabled="saving" @click="saveConfig">{{ saving ? t('saving') : saved ? t('saved') : t('saveAndSend') }}</button></div></div>
          <div v-if="formError" class="alert compact">{{ formError }}</div>
          <div class="curve-selector"><button :class="{ active: activeFanCurve === 'cpu' }" @click="activeFanCurve = 'cpu'"><i class="cpu-line"></i>{{ t('cpuFan') }}</button><button :class="{ active: activeFanCurve === 'hdd' }" @click="activeFanCurve = 'hdd'"><i class="hdd-line"></i>{{ t('hddFan') }}</button></div>
          <div class="fan-chart-wrap">
            <svg class="fan-chart" viewBox="0 0 1000 260" role="img" :aria-label="t('fanCurve')" @pointerdown="beginFanDrag" @pointermove="updateFanFromPointer" @pointerup="endFanDrag" @pointercancel="endFanDrag">
              <g class="chart-grid"><line v-for="value in [0, 25, 50, 75, 100]" :key="`y-${value}`" x1="40" x2="980" :y1="fanPointY(value)" :y2="fanPointY(value)"/><text v-for="value in [0, 25, 50, 75, 100]" :key="`yt-${value}`" x="32" :y="fanPointY(value) + 4" text-anchor="end">{{ value }}%</text><text v-for="item in [{ i: 0, label: '0℃' }, { i: 5, label: '25℃' }, { i: 10, label: '50℃' }, { i: 15, label: '75℃' }, { i: 19, label: '100℃' }]" :key="`x-${item.i}`" :x="fanPointX(item.i)" y="250" text-anchor="middle">{{ item.label }}</text></g>
              <polyline class="curve-line cpu-line" :points="fanCurvePoints('cpu')"/><polyline class="curve-line hdd-line" :points="fanCurvePoints('hdd')"/>
              <circle v-for="(value, index) in form.fanCurves[activeFanCurve]" :key="`${activeFanCurve}-${index}`" class="curve-point" :class="`${activeFanCurve}-point`" :cx="fanPointX(index)" :cy="fanPointY(value)" r="6"/>
            </svg>
          </div>
          <div class="curve-values"><label v-for="(value, index) in form.fanCurves[activeFanCurve]" :key="index"><span>{{ fanTemperatureLabel(index) }}</span><div><input type="number" min="0" max="100" step="1" :value="value" @input="setFanValue(activeFanCurve, index, $event.target.value)"><small>%</small></div></label></div>
        </article>
      </section>

      <section v-else-if="activePage === 'system'" class="page-content two-column"><article class="panel-card detail-card"><div class="section-head"><h3>{{ t('system') }}</h3></div><dl><div><dt>{{ t('hostName') }}</dt><dd>{{ system.hostname || '--' }}</dd></div><div><dt>{{ t('operatingSystem') }}</dt><dd>{{ system.osName || '--' }}</dd></div><div><dt>{{ t('processor') }}</dt><dd>{{ system.cpuName || '--' }}</dd></div><div><dt>{{ t('memory') }}</dt><dd>{{ system.memoryName || '--' }}</dd></div></dl></article><article class="panel-card gauge-card"><div><span>{{ t('cpuTemperature') }}</span><strong :class="temperatureClass(system.cpuTemperature)">{{ system.cpuTemperature || 0 }}℃</strong></div><div><span>{{ t('diskTemperature') }}</span><strong :class="temperatureClass(system.hddTemperature)">{{ system.hddTemperature || 0 }}℃</strong></div><div><span>{{ t('cpuFan') }}</span><strong>{{ report.cpuFanSpeed || 0 }}%</strong></div><div><span>{{ t('hddFan') }}</span><strong>{{ report.hddFanSpeed || 0 }}%</strong></div></article></section>

      <section v-else-if="activePage === 'about'" class="page-content two-column"><article class="panel-card detail-card"><div class="section-head"><h3>{{ t('serverBuild') }}</h3></div><dl><div><dt>{{ t('version') }}</dt><dd>{{ status?.build?.version || 'dev' }}</dd></div><div><dt>{{ t('commit') }}</dt><dd>{{ status?.build?.commit || 'unknown' }}</dd></div></dl></article><article class="panel-card detail-card"><div class="section-head"><h3>{{ t('panelConnection') }}</h3><span class="state" :class="panel.connected ? 'state-2' : 'state-0'"><i></i>{{ panel.connected ? t('connected') : t('disconnected') }}</span></div><dl><div><dt>{{ t('product') }}</dt><dd>{{ panel.product || '--' }}</dd></div><div><dt>{{ t('serial') }}</dt><dd>{{ panel.serial || '--' }}</dd></div><div><dt>{{ t('transferState') }}</dt><dd :class="panel.connected ? 'good' : 'warn'">{{ panel.connected ? t('normal') : panel.lastError || t('connecting') }}</dd></div><div><dt>{{ t('latestPage') }}</dt><dd>{{ pageName(report.page) }}</dd></div><div><dt>{{ t('itemIndex') }}</dt><dd>{{ report.itemIndex ?? '--' }}</dd></div></dl></article><article class="panel-card address-card"><div class="section-head"><div><h3>{{ t('accessAddresses') }}</h3><span>{{ t('accessHint') }}</span></div></div><div class="address-list"><div v-for="link in allURLs" :key="`${link.kind}-${link.name}-${link.url}`"><span>{{ link.kind }} · {{ link.name }}</span><code>{{ link.url }}</code></div><p v-if="allURLs.length === 0" class="empty">{{ t('noAddresses') }}</p></div></article></section>

      <section v-else class="page-content"><article class="panel-card settings-card"><div class="section-head"><h3>{{ t('settings') }}</h3><button class="primary" :disabled="saving" @click="saveConfig">{{ saving ? t('saving') : saved ? t('saved') : t('save') }}</button></div><div v-if="formError" class="alert compact">{{ formError }}</div><div class="form-grid"><label><span>{{ t('listenAddress') }}</span><input v-model.trim="form.listen" placeholder=":8080"><small>{{ t('restartRequired') }}</small></label><label><span>{{ t('panelSerial') }}</span><input v-model.trim="form.panelSerial" :placeholder="t('autoSelect')"><small>{{ t('serialHint') }}</small></label><label><span>{{ t('serverVersion') }}</span><input v-model.trim="form.serverVersion" maxlength="9"><small>{{ byteLength(form.serverVersion) }}/9 bytes</small></label><label><span>{{ t('publicScheme') }}</span><select v-model="form.publicScheme"><option value="http">HTTP</option><option value="https">HTTPS</option></select><small>{{ t('schemeHint') }}</small></label><label><span>{{ t('publicPort') }}</span><input v-model.number="form.publicPort" type="number" min="1" max="65535"><small>{{ t('portHint') }}</small></label><label><span>{{ t('proxyPath') }}</span><input v-model.trim="form.basePath" placeholder="/nas-panel"><small>{{ t('proxyHint') }}</small></label></div><div class="links-head"><div><h4>{{ t('automaticAddresses') }}</h4><p>{{ t('automaticHint') }}</p></div></div><div class="address-list compact-list"><div v-for="link in automaticURLs" :key="link.name"><span>{{ link.name }}</span><code>{{ link.url }}</code></div><p v-if="automaticURLs.length === 0" class="empty">{{ t('noAddresses') }}</p></div><div class="links-head"><div><h4>{{ t('extraLinks') }}</h4><p>{{ t('extraHint') }}</p></div><button class="secondary" @click="addLink">{{ t('addLink') }}</button></div><div class="link-list"><div v-for="(link, index) in form.links" :key="index" class="link-row"><span class="link-number">{{ String(index + 1).padStart(2, '0') }}</span><input v-model.trim="link.name" :aria-label="t('linkName')" :placeholder="t('linkName')"><div class="url-input"><input v-model.trim="link.url" :aria-label="t('linkURL')" placeholder="https://"><small :class="{ over: byteLength(link.url) > 49 }">{{ byteLength(link.url) }}/49</small></div><button class="remove" :aria-label="t('removeLink')" @click="removeLink(index)">×</button></div><p v-if="form.links.length === 0" class="empty">{{ t('noLinks') }}</p></div></article></section>
    </main>
  </div>
</template>
