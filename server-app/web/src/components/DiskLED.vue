<script setup>
import { computed, onMounted, onBeforeUnmount, ref, watch } from 'vue'

const props = defineProps({ disks: { type: Array, default: () => [] }, connected: Boolean, t: Function, apiBase: String })
const emit = defineEmits(['saved'])
const clone = (v) => JSON.parse(JSON.stringify(v))
const emptyBinding = () => ({ path: '', uuid: '', useUUID: false, states: [0, 0, 0], standby: 0 })
const config = ref(null)
const calibration = ref(null)
const binding = ref(null)
const saving = ref(false)
const error = ref('')
const testing = ref(false)
const testMessage = ref('')
const palette = ['red', 'blue', 'green', 'yellow', 'orange', 'white', 'purple', 'cyan']
let testTimer
const colorCSS = { red: '#e35b65', blue: '#369be8', green: '#31ad76', yellow: '#e7be29', orange: '#ef9239', white: '#e8eff6', purple: '#a36bdd', cyan: '#36bec9' }

async function request(path, method = 'GET', body) {
  const response = await fetch(`${props.apiBase}/api/v1/led${path}`, {
    method, headers: { 'Content-Type': 'application/json' },
    ...(body ? { body: JSON.stringify(body) } : {}),
  })
  const data = await response.json()
  if (!response.ok) throw new Error(data.error || `HTTP ${response.status}`)
  return data
}
async function load() {
  try { config.value = await request(''); error.value = '' } catch (e) { error.value = e.message }
}
onMounted(load)
onBeforeUnmount(() => { clearTimeout(testTimer) })
const owner = (b) => props.disks.find((d) => b.useUUID ? b.uuid && d.uuid === b.uuid : b.path && d.path === b.path)
const slotFor = (disk) => config.value?.bindings.findIndex((b) => b.useUUID ? b.uuid && b.uuid === disk.uuid : b.path === disk.path) ?? -1
const offlineBindings = computed(() => (config.value?.bindings ?? []).map((b, index) => ({ ...b, index })).filter((b) => b.path && !owner(b)))
function nameOfState(position, state, colors = config.value?.colors) {
  if (!state || !colors) return props.t('ledOff')
  const c = colors[position]
  return [state & 1 ? props.t('ledColor_' + c.color0) : '', state & 2 ? props.t('ledColor_' + c.color1) : ''].filter(Boolean).join(' + ')
}
function standbyLabel(position, mode) {
  return mode ? props.t('ledBlink', { color: nameOfState(position, mode) }) : props.t('ledOff')
}
function openCalibration() { error.value = ''; calibration.value = clone(config.value) }
function syncColors() {
  if (calibration.value?.sameColors) {
    for (let i = 1; i < 4; i++) calibration.value.colors[i] = { ...calibration.value.colors[0] }
  }
}
watch(() => calibration.value?.sameColors, syncColors)
watch(() => calibration.value?.colors[0], syncColors, { deep: true })
async function persist(next) {
  saving.value = true; error.value = ''
  try {
    config.value = await request('', 'PUT', next)
    emit('saved', clone(config.value))
    return true
  } catch (e) { error.value = e.message; return false } finally { saving.value = false }
}
async function saveCalibration() {
  if (calibration.value.colors.some((c) => c.color0 === c.color1)) { error.value = props.t('ledDifferentColors'); return }
  if (await persist(calibration.value)) calibration.value = null
}
async function test(position, state) {
  testing.value = true; error.value = ''
  try {
    await request('/test', 'POST', { position, state })
    clearTimeout(testTimer)
    testMessage.value = state ? props.t('ledTestActive', { position: position + 1 }) : ''
    if (state) testTimer = setTimeout(() => { testMessage.value = '' }, 5000)
  } catch (e) { error.value = e.message } finally { testing.value = false }
}
function editBinding(disk) {
  error.value = ''
  const old = slotFor(disk)
  binding.value = {
    disk, old, position: old >= 0 ? old : 0,
    useUUID: old >= 0 ? config.value.bindings[old].useUUID : false,
    states: old >= 0 ? [...config.value.bindings[old].states] : [2, 3, 1],
    standby: old >= 0 ? config.value.bindings[old].standby || 0 : 0,
  }
}
function changeState(index, event) {
  const value = Number(event.target.value)
  const current = binding.value.states
  const other = current.indexOf(value)
  const next = [...current]
  if (other >= 0 && other !== index) next[other] = current[index]
  next[index] = value
  binding.value.states = next
}
async function saveBinding() {
  const edit = binding.value
  const occupant = config.value.bindings[edit.position]
  if (occupant.path && edit.position !== edit.old) {
    if (!window.confirm(props.t('ledReplace', { position: edit.position + 1, disk: owner(occupant)?.path || occupant.path }))) return
  }
  const next = clone(config.value)
  if (edit.old >= 0) next.bindings[edit.old] = emptyBinding()
  next.bindings[edit.position] = { path: edit.disk.path, uuid: edit.disk.uuid || '', useUUID: edit.useUUID, states: [...edit.states], standby: edit.standby }
  if (await persist(next)) binding.value = null
}
async function unbind(position) {
  const next = clone(config.value)
  next.bindings[position] = emptyBinding()
  await persist(next)
}
</script>

<template>
  <article class="panel-card led-card">
    <div class="section-head"><div><h3>{{ t('ledTitle') }}</h3><p>{{ t('ledHint') }}</p></div><button class="secondary" :disabled="!config || saving" @click="openCalibration">{{ t('ledSettings') }}</button></div>
    <div v-if="error" class="alert compact" role="alert">{{ error }}</div>
    <button v-if="!config" class="secondary" @click="load">{{ t('ledRetry') }}</button>
    <template v-else>
      <div class="led-slots">
        <div v-for="(b, index) in config.bindings" :key="index" class="led-slot">
          <strong>LED {{ index + 1 }}</strong>
          <span>{{ b.path ? owner(b)?.path || b.path : t('ledUnbound') }}</span>
          <small>{{ !b.path ? t('ledOff') : !owner(b) ? t('ledOffline') : owner(b).standby ? t('diskStandby') + ' · ' + standbyLabel(index, b.standby) : !owner(b).smartAvailable ? t('ledUnknown') : nameOfState(index, b.states[owner(b).status]) }}</small>
          <button v-if="b.path" class="secondary" :disabled="saving" @click="unbind(index)">{{ t('ledUnbind') }}</button>
        </div>
      </div>
      <div class="table-wrap"><table><thead><tr><th>{{ t('device') }}</th><th>{{ t('ledPosition') }}</th><th>{{ t('ledBinding') }}</th><th>{{ t('ledMapping') }}</th><th></th></tr></thead><tbody>
        <tr v-for="disk in disks" :key="disk.path">
          <td><b>{{ disk.path }}</b></td>
          <td>{{ slotFor(disk) >= 0 ? `LED ${slotFor(disk) + 1}` : t('ledUnbound') }}</td>
          <td>{{ slotFor(disk) >= 0 && config.bindings[slotFor(disk)].useUUID ? t('ledStable') : t('ledPath') }}</td>
          <td><template v-if="slotFor(disk) >= 0"><span v-for="(key, state) in ['diskGood','diskWarning','diskFailure']" :key="key" class="led-state-label">{{ t(key) }}: {{ nameOfState(slotFor(disk), config.bindings[slotFor(disk)].states[state]) }}</span><span class="led-state-label">{{ t('diskStandby') }}: {{ standbyLabel(slotFor(disk), config.bindings[slotFor(disk)].standby) }}</span></template><span v-else>—</span></td>
          <td><button class="secondary" :disabled="saving" @click="editBinding(disk)">{{ t('ledBind') }}</button></td>
        </tr>
        <tr v-if="!disks.length"><td colspan="5" class="empty">{{ t('noStorage') }}</td></tr>
        <tr v-for="b in offlineBindings" :key="'offline'+b.index"><td>{{ b.path }} · {{ t('ledOffline') }}</td><td>LED {{ b.index + 1 }}</td><td>{{ b.useUUID ? t('ledStable') : t('ledPath') }}</td><td>{{ t('ledOff') }}</td><td><button class="secondary" :disabled="saving" @click="unbind(b.index)">{{ t('ledUnbind') }}</button></td></tr>
      </tbody></table></div>
    </template>
  </article>

  <div v-if="calibration || binding" class="led-overlay" @keydown.esc="!saving && (calibration = null, binding = null)">
    <section class="panel-card led-dialog" role="dialog" aria-modal="true" :aria-label="t(calibration ? 'ledSettings' : 'ledBind')" tabindex="-1">
      <div class="section-head"><h3>{{ t(calibration ? 'ledSettings' : 'ledBind') }}</h3><button class="secondary" :disabled="saving" @click="calibration = null; binding = null">{{ t('ledClose') }}</button></div>
      <div v-if="error" class="alert compact" role="alert">{{ error }}</div>
      <template v-if="calibration">
        <p>{{ t('ledCalibrationHint') }}</p>
        <label class="led-check"><input v-model="calibration.sameColors" type="checkbox" :disabled="saving">{{ t('ledSameColors') }}</label>
        <div class="table-wrap"><table class="led-calibration"><thead><tr><th></th><th v-for="i in 4" :key="i">LED {{ i }}</th></tr></thead><tbody>
          <tr v-for="(channel, row) in ['color0','color1']" :key="channel"><th>{{ channel }}</th><td v-for="(colors, index) in calibration.colors" :key="index">
            <label class="led-color-input"><i :style="{ background: colorCSS[colors[channel]] }"></i><select v-model="colors[channel]" :disabled="saving || (calibration.sameColors && index > 0)" :aria-label="`LED ${index+1} ${channel}`"><option v-for="color in palette" :key="color" :value="color">{{ t('ledColor_'+color) }}</option></select></label>
            <button class="secondary" :disabled="!connected || testing" @click="test(index, 1 << row)">{{ t('ledTest') }}</button>
          </td></tr>
        </tbody></table></div>
        <p v-if="!connected" class="warn">{{ t('ledPanelRequired') }}</p>
        <p aria-live="polite">{{ testMessage }}</p>
        <div class="led-actions"><button class="secondary" :disabled="!connected || testing" @click="test(0, 0)">{{ t('ledStopTest') }}</button><button class="primary" :disabled="saving" @click="saveCalibration">{{ saving ? t('saving') : t('save') }}</button></div>
      </template>
      <template v-else-if="binding">
        <p><b>{{ binding.disk.path }}</b></p>
        <label class="led-field">{{ t('ledPosition') }}<select v-model.number="binding.position" :disabled="saving"><option v-for="(b, index) in config.bindings" :key="index" :value="index">LED {{ index + 1 }}{{ b.path ? ' · '+(owner(b)?.path || b.path) : '' }}</option></select></label>
        <label class="led-check"><input v-model="binding.useUUID" type="checkbox" :disabled="!binding.disk.uuid || saving">{{ t('ledUseUUID') }}</label>
        <small class="led-id">{{ binding.disk.uuid || t('ledNoUUID') }}</small><p>{{ t('ledUUIDHint') }}</p>
        <div class="led-mapping"><label v-for="(key, state) in ['diskGood','diskWarning','diskFailure']" :key="key" class="led-field">{{ t(key) }}<select :value="binding.states[state]" :disabled="saving" @change="changeState(state, $event)"><option v-for="value in [1,2,3]" :key="value" :value="value">{{ nameOfState(binding.position, value) }}</option></select></label></div>
        <p>{{ t('ledUniqueHint') }}</p>
        <label class="led-field">{{ t('diskStandby') }}<select v-model.number="binding.standby" :disabled="saving"><option v-for="mode in [0,1,2]" :key="mode" :value="mode">{{ standbyLabel(binding.position, mode) }}</option></select></label>
        <p>{{ t('ledStandbyHint') }}</p>
        <div class="led-actions"><button class="primary" :disabled="saving" @click="saveBinding">{{ saving ? t('saving') : t('save') }}</button></div>
      </template>
    </section>
  </div>
</template>

<style scoped>
.led-card { padding: 24px; margin-top: 18px; }
.led-card p, .led-dialog p { color: var(--muted); font-size: 13px; line-height: 1.6; }
.led-slots { display: grid; grid-template-columns: repeat(4, minmax(0,1fr)); gap: 12px; margin: 20px 0; }
.led-slot { border: 1px solid var(--line); border-radius: 12px; padding: 16px; display: flex; flex-direction: column; gap: 10px; overflow-wrap: anywhere; }
.led-slot small { color: var(--muted); }
.led-state-label { display: block; font-size: 12px; line-height: 1.8; }
.led-overlay { position: fixed; inset: 0; z-index: 100; background: #07152299; display: flex; align-items: center; justify-content: center; padding: 24px; }
.led-dialog { width: min(900px, 100%); max-height: 90vh; overflow: auto; padding: 28px; background: var(--surface); }
.led-check { display: flex; align-items: center; gap: 10px; margin: 18px 0 10px; }
.led-check input { width: 18px; height: 18px; }
.led-field { display: flex; flex-direction: column; gap: 10px; }
.led-field select, .led-color-input select { width: 100%; min-height: 40px; color: var(--text); background: var(--surface-soft); border: 1px solid var(--line); border-radius: 8px; padding: 8px; }
select:disabled { opacity: .5; }
.led-calibration { min-width: 480px; width: 100%; table-layout: fixed; }
.led-calibration th:first-child { width: 65px; }
.led-calibration td { padding: 8px; }
.led-calibration button { margin-top: 12px; }
.led-color-input { display: flex; align-items: center; gap: 8px; }
.led-color-input i { flex: 0 0 12px; height: 12px; border-radius: 50%; border: 1px solid #8888; }
.led-actions { display: flex; justify-content: flex-end; gap: 12px; margin-top: 22px; }
.led-mapping { display: grid; grid-template-columns: repeat(3,1fr); gap: 16px; margin-top: 22px; }
.led-id { display: block; overflow-wrap: anywhere; color: var(--muted); }
@media(max-width: 700px) { .led-slots { grid-template-columns: repeat(2,minmax(0,1fr)); } .led-mapping { grid-template-columns: 1fr; } .led-dialog { padding: 18px; } .led-overlay { padding: 10px; } }
</style>
