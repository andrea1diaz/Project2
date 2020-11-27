<template>
	<div id="result">
		<div class="hashtags">
			<div id="hashtags-title">Words</div>
			<div id="hashtags">
				<div
					id="word"
					v-for="word in words"
					v-bind:key="word"
				>
				{{ word }}
				</div>
			</div>
		</div>
		<div class="content">
			<div id="search-results-title">Resultados</div>
			<div id="words" :key="componentKey">
				<div
					v-for="i in results"
					v-bind:key= i
				>
					{{ i }}
				</div>
			</div>
		</div>
	</div>
</template>

<script>
	import { mapState, mapActions } from 'vuex'

	export default {
		name: 'Result',
		props: {
			results: Array,
			componentKey: {
				default: 0
			},
			send: {
				default: false
			}
		},
		data : function () {
			return {
				to_find: "",
			}
		},
		computed: {
			...mapState('collection', ['words'])
		},
		created: function () {
			this.fetchCollections()
		},
		methods: {
			...mapActions('collection', ['getWords']),
			fetchCollections: async function () {
				await this.getWords()
			},
		}
	}
</script>

<style scoped>
	#result {
		margin: 20px;
		height: calc(100% - 121px);
	}

	#title {
		font-size: 25px;
	}

	.hashtags {
		height: -webkit-fill-available;
		width: 20%;
		float: left;
		background-color: #BADFD9;
		border: solid black 3px;
		border-radius: 8px;
	}

	.content {
		display: inline-block;
		margin-left: 30px;
		float: left;
		width: calc(100% - 20% - 40px);
		height: 100%;
	}

	.btn-upload {
		position: absolute;
		bottom: 34px;
		left: 187px;
		background-color: #EAE4D8;
		border: solid black 3px;
		border-radius: 8px;
		width: 65px;
		padding: 3px 8px;
	}

	.btn-upload:hover {
		cursor: pointer;
	}
	
	#hashtags-title {
		margin-top: 10px;
		font-size: 18px;
		font-weight: 900;
	}


	#words {
		background-color: #F4D5D3;
		border: solid black 3px;
		border-radius: 8px;
		height: calc(100% - 53px);
		overflow: scroll;
	}

	#search-results {
		margin-top: 20px;	
	}

	#search-results-title {
		font-size: 20px;
		font-weight: bold;
		margin-bottom: 20px;
	}

	#hashtags {
		overflow: scroll;
		height: 93%;
	}
</style>
